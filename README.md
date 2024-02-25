# CppEnvLoader
A simple C++ environment variable loader.

## Usage
**.env**
```
foo=bar
```

**main.cpp**
```cpp
#include <iostream>
#include "Env.h"

int main()
{
	env::loadEnv(".env");
	std::cout << "foo: " << env::get("foo") << std::endl;
}
```

**Output**
```
foo: bar
```

## Installation
Add a reference to CppEnvLoader.lib.