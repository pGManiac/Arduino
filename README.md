### Schreibrechte auf Arduino
sudo chmod a+rw /dev/ttyUSB0 
    fügt Rechte für USB Schnittstelle zu
    muss jedes Mal neu ausgeführt werden (bei reboot)

in Arduino IDE:

Tools -> Processor -> ATMega328P (Old Bootloader)

### Logicanalyser:

Mit Gerät verbinden -> Gerät suchen, das hinten auf logic analyser steht -> auswählen

Mit den zwei Feldern oben rechts ausprobieren

### Kommandos zum Ausführen
cat input.txt | ./TestExec | tee output.txt

Dieses Kommando leitet den Inhalt der Datei an das Programm und schreibt mit dem tee die Ausgabe auf die Konsole und in das output.txt file. 


dd if=/dev/urandom of=output.bin bs=1 count=50

hexdump -C xxx.bin




SCP:

sudo systemctl start sshd

sudo systemctl status sshd


whoami

time scp source_file username@destination_ip:destination_path	
