@echo Copyright 2019 Tihran Katolikian

@echo You need to have generatorpackage installed for this script.

cd ../SleepEngine/generator
@echo Regenerating files...
pipenv run generate_textures_enum_definition
cd ../../scripts
@echo Finished.
