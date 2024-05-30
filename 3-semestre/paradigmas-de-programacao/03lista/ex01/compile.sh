rm -rf build
javac -d build src/Main.java
cd build
jar cmvf ../MANIFEST.MF MyJar.jar *
cd ..
