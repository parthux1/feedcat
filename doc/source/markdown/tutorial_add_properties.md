# Define custom Properties

1. Derive from PropertyInterface
2. Add custom member variables and functions

## Example usage
### Get your property
```cpp
#include <article.hpp>
#include <MyPropertyType.hpp>

Article article;
// ...
std::optional<MyPropertyType*> prop = article->get<MyPropertyType>();
```

# Define DB-Interactions for custom Properties

You need to implement template-function overloads/specializations of functions defined in 
`src/backend/property_save_templates.hpp` for your custom Property.

To check if all requirements for DB-interactions are met use the concept `PropertyDbStrategy`:
```C++
static_assert(PropertyDbStrategy<MyPropertyType>);
```