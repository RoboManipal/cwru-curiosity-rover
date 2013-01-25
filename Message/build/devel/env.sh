#!/usr/bin/env sh
# generated from catkin/cmake/templates/env.sh.in

if [ $# -eq 0 ] ; then
  /bin/echo "Entering environment at '/home/eddie/code/workspace/sandbox/cwru-curiosity-rover/Message/build/devel', type 'exit' to leave"
  . "/home/eddie/code/workspace/sandbox/cwru-curiosity-rover/Message/build/devel/setup.sh"
  "$SHELL" -i
  /bin/echo "Exiting environment at '/home/eddie/code/workspace/sandbox/cwru-curiosity-rover/Message/build/devel'"
else
  . "/home/eddie/code/workspace/sandbox/cwru-curiosity-rover/Message/build/devel/setup.sh"
  exec "$@"
fi
