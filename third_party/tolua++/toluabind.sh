
pushd ./ #1

cd `dirname $0`

TOLUA_PATH=src/bin
echo "start for '$TOLUA_PATH'..."

bin/toluaapp -C -o "$TOLUA_PATH/toluabind.c" -H "$TOLUA_PATH/toluabind.h" -n tolua "$TOLUA_PATH/tolua_scons.pkg"

echo finished.

popd
