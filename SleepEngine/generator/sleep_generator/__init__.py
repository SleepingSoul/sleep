# Copyright 2019 Tihran Katolikian

import os
import json
from .utils import *
from .file_generate_helper import FileGenerateHelper, IndentIncreaser, Commenter, Block


TEXTURES_SECTION_NAME = 'TexturesEnum'
COPYRIGHT_HEADER = '//-------------------------------------------------------\n\
//---- Copyright 2019 Tihran Katolikian -----------------\n\
//-------------------------------------------------------\n\n\n'

def generate_textures_enum_definition():
    '''
    Generates a C++ file with enumeration for each of images in Images folder.
    '''
    read_all_config()

    config = get_config_section(TEXTURES_SECTION_NAME)

    if config is None:
        return

    generated_file_path = f"{config['TargetFolder']}/{config['TargetName']}"

    with open(generated_file_path, 'w') as target_file:

        helper = FileGenerateHelper(file=target_file, tab_string='    ', comment_string='//')

        image_address_table = {}

        helper.put(COPYRIGHT_HEADER)
        helper.put('#pragma once\n\n')
        helper.put('namespace slp\n')

        with Block(helper, '{\n', '}\n'):

            with IndentIncreaser(helper) as namespace_slp:

                helper.put(f"enum class {config['EnumName']} : {config['UnderlyingType']}\n")

                with Block(helper, '{\n', '};\n'):

                    image_formats = config['AllowedFormats']

                    with IndentIncreaser(helper) as enumImages:

                        enum_value = 0

                        direct_data_path = config['TexturesFolder'][3:]

                        for filename in os.listdir(config['TexturesFolder']):

                            img_name, img_format = filename.split('.')

                            if img_format not in image_formats:
                                continue
                            if enum_value == 0:
                                helper.put(f'  {img_name} = 0\n')
                            else:
                                helper.put(f', {img_name}\n')

                            image_address_table[enum_value] = f'{direct_data_path}/{filename}'

                            enum_value += 1
            
        

        helper.put('\n\n')
        with Commenter(helper):
            helper.put('END OF GENERATED FILE.')
        helper.put('\n')

    print(f'Success: file {generated_file_path} was generated.')

    generate_textures_address_table(config, image_address_table)

    print('-------------------------------------------')

def generate_textures_address_table(config, table):
    '''
    Generates a file that contains pairs: enum underlying type value -> image path.
    It is used for image preloading in C++.
    '''

    print('Generating textures address table...')

    table_file_path = f"{config['TargetFolder']}/{config['TableFileName']}"

    try:
        with open(table_file_path, 'w') as table_file:

            json.dump(table, table_file)
    except Exception as e:
        print(f'Failure: {e}')
        print('-------------------------------------------')
    else:
        print(f'Success: file {table_file_path} was generated.')
