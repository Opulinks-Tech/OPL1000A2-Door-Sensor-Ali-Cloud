## Function / Feature
- This reference realizes sensor type product and uploading to cloud periodically function. 
- Ali could MQTT protocol is supported.
- Single chip solution, application runs on OPL1000 M3 MCU.
- Adopt BLE configure WIFI AP to connect Internet / cloud. 
- Smart sleep and auto-connection are support. 
 
 
## Work Frame
![avatar](sensor_frame.PNG)

## Directory and Content 


**prj_src** folder

- Contains reference design source code, include library, implementation c code and project files. 

**Doc** folder

- Contains this reference application guide , Ali key and app generation guide document. 

**FW_Binary** folder

- Contains m0 bin file and pack script file that used to generate an integrated firmware.
- opl1000.bin: OPL1000 integrated firmware file. User can download it to "door sensor" type device and evaluate its function directly. 
- Note: in order to avoid device "Ali Key 5 elements" conflict, user shall apply new "Ali Key 5 elements" from Ali cloud. Refer "OPL1000_ali_key&app_create_guide.pdf" document to know detailed information.  


## Develop application based on reference

User can develop sensor type application based on provided reference design. Generally it includes 4 steps.

1.  Register and create product/device on Ali cloud, define its property and get  "5 elements set" parameters for application development. 
2.  Modify / extend functions based on existing reference design.
3.  Create Ali cloud function APP . 
4.  Verify message transferring  between IOT device, cloud and mobile APP, and validate functions / features.  
