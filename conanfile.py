import os

from conan import ConanFile
from conan.tools.cmake import cmake_layout
from conan.tools.files import copy


class Tavern(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeToolchain", "CMakeDeps"

    def requirements(self):
        self.requires("glm/1.0.1")
        self.requires("glfw/3.4")
        self.requires("nlohmann_json/3.12.0")
        self.requires("assimp/5.4.3")
        self.requires("spdlog/1.16.0")
        self.requires("stb/cci.20230920")
        self.requires("glad/0.1.36")
        self.requires("imgui/1.92.4-docking")

    def configure(self):
        self.options["glfw"].shared = True

    def generate(self):
        copy(
            self,
            "*glfw*",
            os.path.join(self.dependencies["imgui"].package_folder, "res", "bindings"),
            os.path.join(self.source_folder, "Taverner", "vendor", "imgui", "bindings"),
        )
        copy(
            self,
            "*opengl3*",
            os.path.join(self.dependencies["imgui"].package_folder, "res", "bindings"),
            os.path.join(self.source_folder, "Taverner", "vendor", "imgui", "bindings"),
        )

    def layout(self):
        cmake_layout(self)
