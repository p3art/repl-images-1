# all/
# Template-for-python-without-graphic
#
# 2026-02-06
#
# Show disk usage in the console
#
"""
The shutil module is part of Python's Standard Library. 
You can directly import and use it in your Python scripts.
#
click + to open a new tab, then choose <>Developer
Developer Tools
     Imports
     (Import and manage language-specific packages and dependencies)
"""
import shutil
#
total, used, free = shutil.disk_usage("/home")
print("/home directory...")
print("Total: %d GiB" % (total // (2**30)))
print(" Used: %d GiB" % (used  // (2**30)))
print(" Free: %d GiB" % (free  // (2**30)))
print('')
#
print('Template-for-python-without-graphic')