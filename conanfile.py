from conan import ConanFile
from conan.tools.cmake import CMakeToolchain, CMake, cmake_layout

class libscaleConan(ConanFile):
    name = "libscale"
    version = "1.1.0"

    url = "https://github.com/svnscha/scale-codec-cpp"
    description = "Designing a Better World Through Decentralized Technologies"
    topics = ("crypto", "scale", "substrate", "polkadot")

    # Binary configuration
    settings = "os", "compiler", "build_type", "arch"

    options = {"shared": [True, False]}
    default_options = {
        "shared": False,
        "boost*:header_only": True
    }

    generators = "CMakeDeps"

    # Sources are located in the same place as this recipe, copy them to the recipe
    exports_sources = "CMakeLists.txt", "src/*", "include/*"

    def requirements(self):
        self.requires("boost/1.84.0")

    def generate(self):
        tc = CMakeToolchain(self)
        if self.options.shared:
            tc.variables["BUILD_SHARED_LIBS"] = "ON"
        else:
            tc.variables["BUILD_SHARED_LIBS"] = "OFF"

        tc.variables["BUILD_TESTS"] = "OFF"

        tc.generate()

    def layout(self):
        cmake_layout(self)

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def package(self):
        cmake = CMake(self)
        cmake.install()

    def package_info(self):
        self.cpp_info.libs = ["scale"]
