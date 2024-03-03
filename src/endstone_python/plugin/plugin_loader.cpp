// Copyright (c) 2023, The Endstone Project. (https://endstone.dev) All Rights Reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "endstone/plugin/plugin_loader.h"

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include "endstone/detail/python.h"
#include "endstone/logger.h"
#include "endstone/plugin/plugin.h"
#include "endstone/server.h"

namespace py = pybind11;

namespace endstone::detail {

class PyPluginLoader : public PluginLoader {
public:
    using PluginLoader::PluginLoader;

    std::vector<Plugin *> loadPlugins(const std::string &directory) override
    {
        try {
            PYBIND11_OVERRIDE_PURE_NAME(std::vector<Plugin *>, PluginLoader, "load_plugins", loadPlugins,
                                        std::ref(directory));
        }
        catch (std::exception &e) {
            getServer().getLogger().error("Error occurred when trying to load plugins in '{}': {}", directory,
                                          e.what());
            return {};
        }
    }
};

void def_plugin_loader(py::module &m)
{
    py::class_<PluginLoader, PyPluginLoader>(m, "PluginLoader")
        .def(py::init<Server &>(), py::arg("server"))
        .def("load_plugins", &PluginLoader::loadPlugins, py::arg("directory"),
             py::return_value_policy::reference_internal)
        .def("enable_plugin", &PluginLoader::enablePlugin, py::arg("plugin"))
        .def("disable_plugin", &PluginLoader::enablePlugin, py::arg("plugin"))
        .def_property_readonly("server", &PluginLoader::getServer, py::return_value_policy::reference);
}

}  // namespace endstone::detail