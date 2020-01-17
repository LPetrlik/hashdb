<div style="text-align:right"><img src="https://img.shields.io/badge/maintained-no-red.svg" alt="not maintained"></div>

KarinDB - a fast embeddable key/value database
==============================================

<div style="text-align:right"><img src ="/doc/logo.jpg" width="48" /></div>

KarinDB is a key/value database library specifically designed for fast simultaneous operation of tens to hundreds of instances in a memory-constrained environment.

KarinDB provides the following:

* an embeddable key/value database library written in C++ with a modern C++ API
* fast storage and retrieval - the database is based on the [linear hashing algorithm](https://en.wikipedia.org/wiki/Linear_hashing)
* cross platform - the database has been thoroughly tested on Windows, Linux, and MacOS X (but please see the status below)
* open source with a very permissive [MIT-like open source license](LICENSE.txt)
* code includes an extensive test suite and a modular benchmarking application

The KarinDB database currently does not provide many of the features that might be expected in a traditional high-level database such as client/server access,
a query language, transactions or multi-threaded access to a single database instance.

Status: Windows build is now complete, but new build scripts for POSIX platforms are not yet done.

Sample code:

```C++
#include <iostream>
#include <kerio/hashdb/HashDB.h>
#include <kerio/hashdb/Exception.h>

int main(int argc, char* argv)
{
    using namespace kerio::hashdb;

    try {
        // Open the database.
        Database db = DatabaseFactory();
        db->open("sample", Options::readWriteSingleThreaded());

        // Store three values.
        db->store("key1", 0, "value1");

        db->store("key2", 0, "value2");
        db->store("key2", 1, "value3"); // "value2" and "value3" gets stored to the same bucket.

        // Use an iterator to list all the values.
        for (Iterator it = db->newIterator(); it->isValid(); it->next()) {
            std::cout << "key=" << it->key() << ", "
                      << "part=" << it->partNum() << ", "
                      << "value=" << it->value() << std::endl;
        }
    }
    catch (const kerio::hashdb::Exception& e) {
        std::cout << "Exception: " << e.what() << std::endl;
    }
}
```

KarinDB branches
----------------

There are two main KarinDB branches:

* master branch - for development
* stable - for stable versions.

Other branches serve for development. Please use the stable version for production.


Compiling KarinDB with Visual Studio 2019 or newer
--------------------------------------------------

KarinDB can be compiled with Visual Studio 2019 or newer. If you need to compile KarinDB with a newer version of Visual Studio, 
just let Visual Studio perform the automatic upgrade of KarinDB project files and choose the appropriate toolset when compiling the 
boost libraries.

### 1. Optional step: Installing Python

A Python installation is needed only for running the unit tests. 
If you do not wish to run the unit tests, you can exclude the "tests" project from the build configuration.

Otherwise, install the latest Python version from https://www.python.org/downloads/ .

### 2. Build and test the database library

Now you can build the project. Check that all the unit tests succeeded in the build output window.

### 3. Optional step: Build the sample code

* Add a new console application project to the solution
* In Property Manager, add the property sheet PropSheet\hashdb_headers.props to the new project
* Add references to the "db" and "utils" projects to the new project
* Copy the above sample code
* Compile and run.


Compiling KarinDB on Linux and MacOS X
--------------------------------------

Unfortulately, the original CMake scripts that build KarinDB on Linux and MacOS X depend on proprietary macros that cannot be published, so there is no build support
for these plaforms at this time.
