
template <typename Object, typename ... Args>
Object& State::newGameObject(Args&&... args) {
    auto& v = accessGameObjects<Object>();
    v.emplace_back(std::forward<Args>(args)...);
    return v.back();
}

template <typename Object>
std::vector<Object>& State::getGameObjects() {
    return accessGameObjects<Object>();
}

template <typename Object>
std::vector<Object>& State::accessGameObjects() {
    static std::vector<Object> v;
    return v;
}
