#include <concepts>
#include <iostream>
#include <type_traits>

 
template<typename T>
concept ComplexConcept = requires(const T& obj){
    {obj.hash()} -> std::convertible_to<long>;
    {obj.toString()} -> std::same_as<std::string>;
   
} && !std::has_virtual_destructor_v<T>;


 // Подходящий тип
struct ValidType {
    long hash() const { return 42L; }
    std::string toString() const { return "Valid"; }
    ~ValidType() = default; 
};

// Неподходящий тип (имеет виртуальный деструктор)
struct InvalidType {
    const char* hash() const { return "42L"; }
    std::string toString() const { return "Invalid"; }
    virtual ~InvalidType() = default;
};


 
int main()
{
    static_assert(ComplexConcept<ValidType>);  
    static_assert(!ComplexConcept<InvalidType>); 

    std::cout << "Program finished successfully" << std::endl;	
	return 0; 
}