#include <iostream>
using namespace std;

class CPU {
public:
	CPU() {
		cout << "Processor created, type ";
	}
};

class x64: public CPU {
public:
	x64() :
			CPU() {
		cout << "x64" << endl;
	}
};

class PowerPC: public CPU {
public:
	PowerPC() :
			CPU() {
		cout << "PowerPC" << endl;
	}
};

class Snapdragon: public CPU {
public:
	Snapdragon() :
			CPU() {
		cout << "Snapdragon" << endl;
	}
};


class GPU {
public:
	GPU() {
		cout << "Created GPU, type ";
	}
};

class Nvidia: public GPU {
public:
	Nvidia() :
			GPU() {
		cout << "Nvidia" << endl;
	}
};

class AppleGraphics: public GPU {
public:
	AppleGraphics() :
			GPU() {
		cout << "AppleGraphics" << endl;
	}
};

class Adreno: public GPU {
public:
	Adreno() :
			GPU() {
		cout << "Adreno" << endl;
	}
};


class Drive {
public:
	Drive() {
		cout << "Created storage drive, type ";
	}
};

class HDD: public Drive {
public:
	HDD() :
			Drive() {
		cout << "HDD" << endl;
	}
};

class SSD: public Drive {
public:
	SSD() :
			Drive() {
		cout << "SSD" << endl;
	}
};

class SD: public Drive {
public:
	SD() :
			Drive() {
		cout << "SD Card" << endl;
	}
};


class RAM {

};

class PC {
protected:
	CPU *proc;
	GPU *graphics;
	Drive *drive;
	RAM *memory;
public:
	~PC() {
		if (proc)
			delete proc;
		if (graphics)
			delete graphics;
		if (drive)
			delete drive;
		if (memory)
			delete memory;
	}
	void setCPU(CPU *proc) {
		this->proc = proc;
	}
	void setGPU(GPU *graphics) {
		this->graphics = graphics;
	}
	void setDrive(Drive *drive) {
		this->drive = drive;
	}
	void setRAM(RAM *memory) {
		this->memory = memory;
	}
};

class Win: public PC {
public:
	Win() :
			PC() {
		cout << "Windows PC created" << endl;
	}
};

class Mac: public PC {
public:
	Mac() :
			PC() {
		cout << "Mac PC created" << endl;
	}
};

class Android:public PC{
	Android():PC(){
		cout << "Android device created" << endl;
	}
};

class ConstructorPC {
public:
	virtual CPU* getCPU()=0;
	virtual GPU* getGPU()=0;
	virtual Drive* getDrive()=0;
	virtual RAM* getRAM() {
		return new RAM();
	}

};

class ConstructorWin: public ConstructorPC {
public:
	CPU* getCPU() override {
		return new x64();
	}
	GPU* getGPU() override {
		return new Nvidia();
	}
	Drive* getDrive() override {
		return new HDD();
	}
};

class ConstructorMac: public ConstructorPC {
public:
	CPU* getCPU() override {
		return new PowerPC();
	}
	GPU* getGPU() override {
		return new AppleGraphics();
	}
	Drive* getDrive() override {
		return new SSD();
	}
};

class ConstructorAndroid: public ConstructorPC {
public:
	CPU* getCPU() override {
		return new Snapdragon();
	}
	GPU* getGPU() override {
		return new Adreno();
	}
	Drive* getDrive() override {
		return new SD();
	}
};


class Configurator {
	ConstructorPC *constructor;
public:
	Configurator() {
		this->constructor = NULL;
	}
	Configurator(ConstructorPC *constructor) {
		this->constructor = constructor;
	}
	void setConstructor(ConstructorPC *constructor) {
		this->constructor = constructor;
	}

	void configure(PC *pc) {
		if (constructor) {
			pc->setCPU(constructor->getCPU());
			pc->setGPU(constructor->getGPU());
			pc->setDrive(constructor->getDrive());
			pc->setRAM(constructor->getRAM());
		}
	}

	~Configurator() {
		if (constructor)
			delete constructor;
	}
};

int main() {
	Configurator config;
	PC *pc1 = new PC();
	config.setConstructor(new ConstructorWin);
	config.configure(pc1);
	cout<<"---"<<endl;
	PC *pc2=new PC();
	config.setConstructor(new ConstructorAndroid);
	config.configure(pc2);

	return 0;
}
