set -e

if [[ $# -eq 0 ]] ; then
    echo 'Please provide a strategy name as the first argument and the strategy to copy from as the second argument.'
    exit 0
fi

NAME=$1
LNAME=`echo "$NAME" | tr '[:upper:]' '[:lower:]'`

STRATEGY=$2
STRATEGY=${STRATEGY:-FF16}

echo Making new strategy with name ${NAME} in result/
RScript -e "library(methods); source('./new_strategy.R'); scaffold('${NAME}', '${STRATEGY}')"

echo Strategy $NAME created from $STRATEGY
echo New files created:
echo "\tR/${LNAME}.R"
echo "\tsrc/${LNAME}_strategy.cpp"
echo "\tinst/include/plant/${LNAME}_strategy.h"
echo "\ttests/testthat/test-strategy-${LNAME}.R"
echo
echo Modified Files:
echo "\tinst/include/plant.h"
echo "\tinst/include/RccpR6_classes.yml"
echo "\tsrc/plant_plus.cpp"
echo "\tsrc/plant_tools.cpp"
echo "\ttests/testthat/helper-plant.cpp"
echo "\tR/plant.R"
echo "\tR/scm_support.R"
echo 
echo run the following in the root directory to recompile and test plant.
echo "make clean; make; make test; make install"