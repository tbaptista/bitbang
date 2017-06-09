# BitBang Framework external dependencies

The BitBang Framework uses external libraries, some in source form, and some in binary form. The ones that are used in binary form, are not included in the source code release. These will need to be downloaded, built, and placed in this directory where the build script will look for them.

The needed libraries are:

* [Irrlicht](http://irrlicht.sourceforge.net)
* [Bullet Physics](http://bulletphysics.org)

The expected directory structure is this:
```
external
+-- bullet
|   +-- include
|   +-- lib
+-- irrlicht
    +-- include
	+-- lib	
```

In the future, we expect to setup the cmake script to download and build these dependencies, but for now it has to be done manually.
