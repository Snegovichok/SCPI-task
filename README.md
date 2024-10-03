# SCPI-task
**Steps**:
1) Install the VNA application software (S2VNA):
https://coppermountaintech.com/s2-vna-soft/
And run it in demo mode. You can enable demo mode using these softkeys in the application: System > Misc Setup > Demo  Mode - ON
Note: Settings during installation isn't important. You can simply click on 'next' until the last step.

2) Enable socket server to allow automating the VNA application. You can enable it using these softkeys in the application: System > Misc Setup > Network Remote Control Settings > Socket Port - 5025 > Socket Server - ON

3) Download the C++ example:
https://coppermountaintech.com/programming-examples/
The example project file is located in this folder: Programming Examples > SCPI > C++ > C++ simple example
The example uses SCPI commands in the VISA library to automate the measurements. "How to link visa library.txt" is an important document to refer to make the program work.

**Various terminal readings**
Here are the tests of the program and the very characteristics of the computer on which the calculations were performed.
