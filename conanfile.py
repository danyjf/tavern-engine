from conan import ConanFile
from conan.tools.cmake import cmake_layout


class Tavern(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeToolchain", "CMakeDeps"

    def requirements(self):
        self.requires("glm/1.0.1")
        self.requires("glfw/3.4")

    def configure(self):
        self.options["glfw"].shared = True

    def layout(self):
        cmake_layout(self)
