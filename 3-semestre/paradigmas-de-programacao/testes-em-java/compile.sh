javac -d build Main.java bla/Person.java
cd build
jar cmvf ../MANIFEST.MF MyJar.jar *
cd ..
