from conans import ConanFile, CMake, tools


class samna(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    requires = [("spdlog/1.8.2")]

    generators = "cmake", "cmake_find_package", "virtualrunenv"

    def imports(self):
        self.copy("*.dll", dst="bin", src="bin")
        self.copy("*.dylib*", dst="lib", src="lib")
        self.copy("*.so*", dst="lib", src="lib")
