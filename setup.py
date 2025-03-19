from setuptools import setup, find_packages
import glob

setup(
    name="matrix_package",
    version="0.1",
    packages=find_packages(),
    package_data={"matrix_ops": ["matrix_module*.so"]},  # Include the compiled module
    include_package_data=True,
)