import sys

sExt = "sh"
bIsWindows = sys.platform.startswith('win')
if(bIsWindows):
    sExt = "bat"
else:
    sExt = "sh"
print(sExt)