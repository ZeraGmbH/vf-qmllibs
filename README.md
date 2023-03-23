# vf-qmllibs

provides qml component libs and qml application libs for guis

## Setup Project
Following folders must be set:

* CMAKE_PREFIX_PATH=/usr
* CMAKE_INSTALL_PREFIX=/usr
* CMAKE_INSTALL_SYSCONFDIR=/etc
* QML_IMPORT_PATH=/usr/lib64/qt5/qml

CMAKE_PREFIX_PATH has to be equal to /usr;${CMAKE_INSTALL_PREFIX}.
It is recommendet to set the variables not to the hosts systemroot.

For example use:

CMAKE_PREFIX_PATH=/usr;/${some}/${folder}/usr
CMAKE_INSTALL_PREFIX=/${some}/${folder}/usr
CMAKE_INSTALL_SYSCONFDIR=/${some}/${folder}/etc
QML_IMPORT_PATH=${CMAKE_INSTALL_LIBDIR}/zera-qml-modules

### in Terminal 

To setup the Project in your terminal go to your desired build location and call:

```
cmake -DCMAKE_PREFIX_PATH="/usr;${install_dir}" -DCMAKE_INSTALL_PREFIX="${install_dir}"  
-DCMAKE_INSTALL_SYSCONFDIR="${config_dir}" -DQML_IMPORT_PATH=${CMAKE_INSTALL_LIBDIR}/zera-qml-modules -S /<path>/<to>/<repo>
```

To build the project call 

```
make -j8
```
in your build directory.


### in qt Creator

* Go to open project and choose the toplevel CMakeLists.txt
* Configure project
* Go to Projects 
* Add the required cmake and qml variables and set them as described above
* Run CMake 
* Build 

