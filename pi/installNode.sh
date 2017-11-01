echo 'Instalando node no Pi ...'

curl -sLS https://apt.adafruit.com/add | sudo bash
sudo apt-get install node

echo 'Node instalado, versao: ' 
node -v
