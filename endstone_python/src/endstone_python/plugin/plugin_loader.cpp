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

#include "endstone/logger.h"
#include "endstone/plugin/plugin.h"
#include "endstone/server.h"
#include "endstone_python/endstone_python.h"

namespace py = pybind11;

class PyPluginLoader : public PluginLoader, public py::trampoline_self_life_support {
public:
    using PluginLoader::PluginLoader;

    std::unique_ptr<Plugin> loadPlugin(const std::string &file) noexcept override
    {
        try {
            PYBIND11_OVERRIDE_PURE_NAME(std::unique_ptr<Plugin>, PluginLoader, "load_plugin", loadPlugin,
                                        std::ref(file));
        }
        catch (std::exception &e) {
            getServer().getLogger().error("Failed to load python plugin from {}.", file);
            getServer().getLogger().error(e.what());
            return nullptr;
        }
    }

    [[nodiscard]] std::vector<std::string> getPluginFileFilters() const noexcept override
    {
        try {
            PYBIND11_OVERRIDE_PURE_NAME(std::vector<std::string>, PluginLoader, "get_plugin_file_filters",
                                        getPluginFileFilters);
        }
        catch (std::exception &e) {
            getServer().getLogger().error(e.what());
            return {};
        }
    }
};

void def_plugin_loader(py::module &m)
{
    py::class_<PluginLoader, PyPluginLoader>(m, "PluginLoader")
        .def(py::init<Server &>(), py::arg("server"))
        .def("get_plugin_file_filters", &PluginLoader::getPluginFileFilters)
        .def("load_plugin", &PluginLoader::loadPlugin, py::arg("file"), py::return_value_policy::reference)
        .def("enable_plugin", &PluginLoader::enablePlugin, py::arg("plugin"))
        .def("disable_plugin", &PluginLoader::enablePlugin, py::arg("plugin"))
        .def_property_readonly("server", &PluginLoader::getServer, py::return_value_policy::reference);
}