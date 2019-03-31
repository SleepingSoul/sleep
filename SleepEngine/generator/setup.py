# Copyright 2019 Tihran Katolikian

from setuptools import setup


setup(
    name='sleep_generator',
    description='sleep engine extension for generating custom C++ files.',
    author='Tihran Katolikian',
    entry_points={
        'console_scripts': [
            'generate_images_enum_definition=sleep_generator:generate_images_enum_definition'
        ]
    },
    project_urls={
        'GitHub': 'https://github.com/SleepingSoul/sleep'
    },
)
