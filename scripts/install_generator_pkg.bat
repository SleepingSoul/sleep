@echo Copyright 2019 Tihran Katolikian

@echo You need to have python and pipenv installed to run this script.

cd ../SleepEngine/generator
@echo Installing package...
pipenv install -e .
cd ../../scripts
@echo Finished.
