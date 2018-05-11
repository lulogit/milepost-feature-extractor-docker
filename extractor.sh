# Constants for colored text
RED='\033[0;31m'
GREEN='\033[0;32m'
NC='\033[0m' # No Color

echo -e "${RED}[1/3] Cloning source files to TEMP work dir ... ${NC}"
mkdir -p /TEMP
cp /sources/*.c /TEMP 2> /dev/null
cp /sources/*.h /TEMP 2> /dev/null
cd /TEMP
echo -e "${GREEN}Done! ${NC}"

echo -e "${RED}[2/3] Feature extraction ... ${NC}"
ctuning-cc -O3 *.c --ct-extract-features
echo -e "${GREEN}Done! ${NC}"

echo -e "${RED}[3/3] Copying features to 'features' host dir ...${NC}"
mkdir -p /sources/features
cp /TEMP/*.ft /sources/features 2> /dev/null
echo -e "${GREEN}Done! ${NC}"
