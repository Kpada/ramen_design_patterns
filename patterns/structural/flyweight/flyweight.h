#ifndef __FLYWEIGHT_H__
#define __FLYWEIGHT_H__

#include <initializer_list>
#include <iostream>
#include <map>
#include <memory>
#include <sstream>
#include <string>

#include "../../iPattern.h"

/* GoF design pattern: Flyweight */
namespace Flyweight {

/* Shared state must not give a chance to change its internal state */
class SharedState {
 public:
  SharedState(std::string country, std::string city, std::string postalCode,
              std::string addressLine)
      : m_county(std::move(country)),
        m_city(std::move(city)),
        m_postalCode(std::move(postalCode)),
        m_adressLine(std::move(addressLine)) {
    sharedStateObjCounter++;
  }

  SharedState(const SharedState& state)
      : SharedState(state.m_county, state.m_city, state.m_postalCode,
                    state.m_adressLine) {}

  ~SharedState() { sharedStateObjCounter--; }

  static int GetNumberOfSharedStates() { return sharedStateObjCounter; }

  const std::string& GetCountry() const { return m_county; }

  const std::string& GetCity() const { return m_city; }

  const std::string& GetPostalCode() const { return m_postalCode; }

  const std::string& GetAddressLine() const { return m_adressLine; }

 private:
  const std::string m_county;
  const std::string m_city;
  const std::string m_postalCode;
  const std::string m_adressLine;

  /* Counter of existing objects */
  static int sharedStateObjCounter;
};

int SharedState::sharedStateObjCounter = 0;

std::ostream& operator<<(std::ostream& os, const SharedState& state);

/* Unique state */
class UniqueState {
 public:
  UniqueState(std::string restaurantName, std::string type)
      : m_restaurantName(std::move(restaurantName)), m_type(std::move(type)) {}

  UniqueState(const UniqueState& state)
      : UniqueState(state.m_restaurantName, state.m_type) {}

  const std::string& GetName() const { return m_restaurantName; }

  const std::string& GetType() const { return m_type; }

 private:
  std::string m_restaurantName;
  std::string m_type;
};

std::ostream& operator<<(std::ostream& os, const UniqueState& state);

/* FlyWeight:
 * 1) contains shared data, which belongs to several business-logic objects
 * 2) can do something useful with unique data of these objects
 */
class FlyWeight {
 public:
  explicit FlyWeight(std::shared_ptr<SharedState> state)
      : m_sharedState(std::move(state)) {}

  explicit FlyWeight(const SharedState& state)
      : m_sharedState(std::make_shared<SharedState>(state)) {}

  const std::shared_ptr<SharedState> GetSharedState() const {
    return m_sharedState;
  }

  void Operation(const UniqueState& unique_state) const {
    std::cout << PrinterState::Quote << "FlyWeight operation: shared ("
              << *m_sharedState.get() << ") and unique (" << unique_state
              << ") state.\n";
  }

  static int GetNumberOfSharedStates() {
    return SharedState::GetNumberOfSharedStates();
  }

 private:
  std::shared_ptr<SharedState> m_sharedState;
};

std::ostream& operator<<(std::ostream& os, const FlyWeight& fw);

/**
 * Фабрика Легковесов создает объекты-Легковесы и управляет ими. Она
 * обеспечивает правильное разделение легковесов. Когда клиент запрашивает
 * легковес, фабрика либо возвращает существующий экземпляр, либо создает новый,
 * если он ещё не существует.
 */
class FlyWeightFactory {
 public:
  explicit FlyWeightFactory(std::initializer_list<SharedState> share_states) {
    for (const SharedState& state : share_states) {
      flyweights.insert(std::make_pair(GetSharedKey(state), FlyWeight{state}));
    }
  }

  /* Creates a flyweight for the state if it doesn't exist
   * Returns the flyweight
   */
  FlyWeight GetFlyWeight(const SharedState& state) {
    const std::string key = this->GetSharedKey(state);

    if (flyweights.find(key) == flyweights.end()) {
      std::cout << PrinterState::Quote
                << "FlyWeight Factory: cannot find a flyweight, creating a new "
                   "one.\n";
      flyweights.insert(std::make_pair(key, FlyWeight{state}));
    } else {
      std::cout << PrinterState::Quote
                << "FlyWeight Factory: the flyweight is found, reuse it.\n";
    }

    return this->flyweights.at(key);
  }

  /* Print all the existing flyweights */
  void PrintFlyWeights() const {
    /* the number of lightweights must be equal to
     * the number of shared objects
     */
    std::cout << PrinterState::Quote << "There are " << flyweights.size()
              << " flyweights and " << FlyWeight::GetNumberOfSharedStates()
              << " shared states.\n";

    int counter = 0;
    for (const auto& item : flyweights) {
      std::cout << PrinterState::Quote << ++counter << ") " << item.second
                << "\n";
    }
  }

 private:
  /* it's better to use the std::unordered_map and std::hash */
  std::map<std::string, FlyWeight> flyweights;

  std::string GetSharedKey(const SharedState& state) const {
    std::stringstream ss;
    ss << state.GetCountry() << "_" << state.GetPostalCode() << "_"
       << state.GetCity() << "_" << state.GetAddressLine();
    return ss.str();
  }
};

std::ostream& operator<<(std::ostream& os, const SharedState& state) {
  return os << "[" << state.GetCountry() << " / " << state.GetCity() << " / "
            << state.GetPostalCode() << " / " << state.GetAddressLine() << "]";
}

std::ostream& operator<<(std::ostream& os, const UniqueState& state) {
  return os << "[" << state.GetName() << " / " << state.GetType() << "]";
}

std::ostream& operator<<(std::ostream& os, const FlyWeight& fw) {
  return os << *fw.GetSharedState().get();
}

struct RestaurantInfo {
  /* specific info */
  std::string name;
  std::string type;
  /* address */
  std::string country;
  std::string city;
  std::string postalCode;
  std::string addressLine;
};

/* Flyweight Pattern */
class Pattern : public IPattern {
 public:
  Pattern() : IPattern("Flyweight") {}

 private:
  void BusinessLogic() const final {
    std::cout
        << PrinterState::Quote
        << "We are going to develop an app for ramen lovers. We will map "
        << "the best restaurants in the country. "
        << "Obviouly, each restaurant has 2 types of data: "
        << "shared data (its address) and unique data (its name and type). "
        << "To avoid duplicates and save memory resourese we will use "
           "flyweighs.\n";

    std::cout << PrinterState::PlainText << "Creating the factory\n";
    FlyWeightFactory factory = CreateFactory();
    factory.PrintFlyWeights();

    /* add a restaurant to the existing address */
    AddRestaurantToGoogleMap(factory, {"Best-Ramen", "Ramen", "Russia",
                                       "Moscow", "109651", "Pererva, 42"});

    /* add 3 restaurants to the same address */
    AddRestaurantToGoogleMap(factory, {"Ku-Ramen", "Ramen", "Russia", "Moscow",
                                       "123456", "Untitled street, 42"});
    AddRestaurantToGoogleMap(
        factory, {"Best-Gyoza", "Gyoza", "Russia", "Moscow", "123456",
                  "Untitled street, 42"});
    AddRestaurantToGoogleMap(factory, {"Best-Udon", "Udon", "Russia", "Moscow",
                                       "123456", "Untitled street, 42"});

    /* print */
    factory.PrintFlyWeights();
  }

  static FlyWeightFactory CreateFactory() {
    /* we're going to use an existing map, so it's not empty */
    return FlyWeightFactory{
        {"Russia", "Moscow", "103132", "The Kremlin"},
        {"Russia", "St. Petersburg", "190000", "Saint Isaac's Cathedral"},
        {"Russia", "Moscow", "109651", "Pererva, 42"},
    };
  }

  void AddRestaurantToGoogleMap(FlyWeightFactory& factory,
                                const RestaurantInfo& info) const {
    std::cout << PrinterState::PlainText
              << "Adding a restaurant to the map...\n";

    FlyWeight fw = factory.GetFlyWeight(
        {info.country, info.city, info.postalCode, info.addressLine});

    fw.Operation({info.name, info.type});
  }
};

}  // namespace Flyweight

#endif /* __FLYWEIGHT_H__ */
