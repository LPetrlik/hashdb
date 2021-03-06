
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

Please use the stable version for production.


Compiling KarinDB with Visual Studio 2010 or newer
--------------------------------------------------

KarinDB can be compiled with Visual Studio 2010 or newer. If you need to compile KarinDB with a newer version of Visual Studio, 
just let Visual Studio perform the automatic upgrade of KarinDB project files and choose the appropriate toolset when compiling the 
boost libraries.

### 1. Installing boost

If your project already uses boost libraries, you must compile KarinDB with the same boost variant.
Otherwise, you may either download precompiled boost binaries or compile boost from sources.

If you have WGET and UNZIP installed on your system, you can download and compile boost with the included batch file `fetch_compile_boost.bat`:
* Edit the ADDRESS_MODEL and MSVC_TOOLSET variables in the `fetch_compile_boost.bat` batch file.
* Run the batch.

If the above does not work for you, you may download and compile boost manually:
* Download boost 1.62 or newer and unpack it.
* Create directory for the target, e.g. "deps\boost_1_62_0_vs10.0_64"
* Run `bootstrap.bat`
* Run `bjam --prefix=...\deps\deps\boost_1_62_0_vs10.0_64 toolset=msvc-10.0 address-model=64 --without-mpi --without-python --without-graph --without-graph_parallel --without-wave install`

The option `address-model` should be set to either 32 or 64 depending on your compilation target.

### 2. Configuring path to boost headers and libraries

If you use boost version different than 1.62 or if you do not follow the above directory conventions, you need to configure path to boost headers and libraries:
* In Visual Studio 2010, open the solution build\VS2010\KarinDB.sln
* Choose your target platform (Win32 or x64) in the Solution Platforms drop-down list.
* Click on "Property Manager" on the bottom of the left pane (you may need to enable advanced features if you are using VS 2010 Express Edition)
* Expand the "tool" project until you find a property sheet called "boost32" or "boost64" (depending on the chosen address model), and double-click it.
* Edit C/C++ / General / Additional Include Directories, change the path to your boost includes.
* Edit Linker / General / Additional Library Directories, change the to your boost libraries.

### 3. Optional step: Installing Python

A Python installation is needed only for running the unit tests. 
If you do not wish to run the unit tests, you can exclude the "tests" project from the build configuration.

Otherwise, install the latest Python version from https://www.python.org/downloads/ .

### 4. Build and test the database library

Now you can build the project. Check that all the unit tests succeeded in the build output window.

### 5. Optional step: Build the sample code

* Add a new console application project to the solution
* In Property Manager, add property sheets PropSheet\hashdb_headers.props and PropSheet\boost32.props (or boost64) to the new project
* Add references to the "db" and "utils" projects to the new project
* Copy the above sample code
* Compile and run.


Compiling KarinDB on Linux and MacOS X
-------------------------------------

Unfortulately, the original CMake scripts that build KarinDB on Linux and MacOS X depend on proprietary macros that cannot be published, so there is no build support
for these plaforms at this time.
