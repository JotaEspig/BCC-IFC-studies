from distutils.core import setup, Extension
from setuptools import find_packages


def main() -> None:
    setup(
        name="hello",
        version="0.0.1",
        description="hello module has some dumb things",
        author="Jota Cria",
        author_email="jotaespig@gmail.com",
        packages=find_packages(),
        ext_modules=[Extension("hellomod.hellolib", ["src/hellomod.c"])]
    )


if __name__ == "__main__":
    main()
