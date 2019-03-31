# Copyright 2019 Tihran Katolikian

import os
from .utils import *
from .file_generate_helper import FileGenerateHelper, IndentIncreaser, Commenter, Block


IMAGES_SECTION_NAME = 'ImageEnum'

def generate_images_enum_definition():
    '''
    Generates a C++ file with enumeration for each of images in Images folder.
    '''

    read_all_config()

    config = get_config_section(IMAGES_SECTION_NAME)

    if config is None:
        return

    generated_file_path = f"{config['TargetFolder']}/{config['TargetName']}"

    with open(generated_file_path, 'w') as target_file:

        helper = FileGenerateHelper(file=target_file, tab_string='    ', comment_string='//')

        with Commenter(helper):
            helper.put('-------------------------------------------------------\n')
            helper.put('---- Copyright 2019 Tihran Katolikian -----------------\n')
            helper.put('-------------------------------------------------------\n')
        
        helper.put('\n\n')

        helper.put('namespace slp\n')

        with Block(helper, '{\n', '}\n'):

            with IndentIncreaser(helper) as namespace_slp:

                helper.put('enum class Images\n')

                with Block(helper, '{\n', '};\n'):

                    image_formats = config['AllowedFormats']

                    with IndentIncreaser(helper) as enumImages:

                        is_first = True

                        for filename in os.listdir(config['ImagesFolder']):

                            img_name, img_format = filename.split('.')

                            if img_format not in image_formats:
                                continue
                            if is_first:
                                helper.put(f'  {img_name}\n')
                                is_first = False
                            else:
                                helper.put(f', {img_name}\n')
            
        

        helper.put('\n\n')
        with Commenter(helper):
            helper.put('END OF GENERATED FILE.')
        helper.put('\n')

    print(f'Success: file {generated_file_path} was generated.')
    print('-------------------------------------------')
