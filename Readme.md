# Remote objective function call for black-box optimization algorithms testing 
This project involves the development of a web application that allows users to register accounts and remotely invoke a server-side objective function.
The application tracks the number of function calls made by each user and includes an administrative panel for managing user accounts. The administrative panel is accessible exclusively to the administrator.  

## Required Libraries and Tools  

### 1. Boost  
Installation: `sudo apt-get install libboost-all-dev`  

### 2. CMake  
Installation: `sudo apt-get install cmake`  

### 3. Wt (for creating a web application)  
Installation: Run the provided script `wt_installation.sh`. This script installs the library locally within the directory where it is executed, under `/install/wt_install/`.  

### 4. SQLite3  
Installation: `sudo apt install sqlite3 libsqlite3-dev`  

---

## Setting Up the Environment for Wt Dynamic Libraries  
To ensure the system locates Wt dynamic libraries correctly, set the environment variable as follows:  

In the project directory, run the command:  
`export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$(pwd)/install/wt_install/lib/`.  

You can verify the variable is set by running:  
`echo $LD_LIBRARY_PATH`.  

---

## Build and Run Instructions  

### Building the Application  
In the directory containing the source files, execute the following commands:  
`mkdir build`, then `cd build/`, followed by `cmake ..` and `cmake --build .`.  

### Executing the Applications  
Once the build process is complete, the following executable files will be created in the `/build` directory:  
- **TCPServer**: Run using `./TCPServer`.  
- **TCPClient**: Run using `./TCPClient`.  
- **Webapp**: Run using `./Webapp --http-listen 0.0.0.0:8080 --docroot .`.  

---

### Running Tests  
To run the tests, navigate to the `/build` directory and execute the command `ctest`.  
