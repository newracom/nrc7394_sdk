CURRENT=$(pwd)
pushd ../../../../lib/nanopb/src/generator
python3 nanopb_generator.py --output-dir=$CURRENT/../ -I $CURRENT link_status.proto
popd
