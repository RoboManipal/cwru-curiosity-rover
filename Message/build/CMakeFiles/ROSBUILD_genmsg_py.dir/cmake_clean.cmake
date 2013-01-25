FILE(REMOVE_RECURSE
  "../src/Message/msg"
  "CMakeFiles/ROSBUILD_genmsg_py"
  "../src/Message/msg/__init__.py"
  "../src/Message/msg/_InitalPosition.py"
)

# Per-language clean rules from dependency scanning.
FOREACH(lang)
  INCLUDE(CMakeFiles/ROSBUILD_genmsg_py.dir/cmake_clean_${lang}.cmake OPTIONAL)
ENDFOREACH(lang)
