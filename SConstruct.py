#!/usr/bin/env python
import os
import sys

target_path = ARGUMENTS.pop("target_path", "demo/addons/gdredis/bin/")
target_name = ARGUMENTS.pop("target_name", "libgdredis")

env = SConscript("godot-cpp/SConstruct")

target = "{}{}".format(
    target_path, target_name
)

# For reference:
# - CCFLAGS are compilation flags shared between C and C++
# - CFLAGS are for C-specific compilation flags
# - CXXFLAGS are for C++-specific compilation flags
# - CPPFLAGS are for pre-processor flags
# - CPPDEFINES are for pre-processor defines
# - LINKFLAGS are for linking flags

sources = [Glob("src/*.cpp")]
# hiredis = Glob("lib/hiredis/*.c")
# openssl = Glob("lib/openssl/*.c")

# sources.extend(hiredis)
# sources.extend(openssl)

# tweak this if you want to use different folders, or more folders, to store your source code in.
includes = [
    "src/",
    # "lib/hiredis/",
    # "/opt/homebrew/Cellar/hiredis/1.2.0/include",
    # "/opt/homebrew/Cellar/openssl@3/3.1.3/include"
]
env.Append(CPPPATH=includes)
# env.Append(LIBPATH=["./lib/hiredis"])
# env.Append(LIBS=["hiredis", "openssl"])

if env["platform"] == "macos":
    target = "{}.{}.{}.framework/{}.{}.{}".format(
        target,
        env["platform"],
        env["target"],
        target_name,
        env["platform"],
        env["target"]
    )
else:
    target = "{}{}{}".format(
        target,
        env["suffix"],
        env["SHLIBSUFFIX"]
    )

library = env.SharedLibrary(target=target, source=sources)

Default(library)
