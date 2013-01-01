#include <Wt/WApplication>
#include <Wt/WBreak>
#include <Wt/WContainerWidget>
#include <Wt/WGroupBox>
#include <Wt/WText>
#include <Wt/WSpinBox>
#include <Wt/WTable>
#include "Aquarius.h"
#include "LEDChannel.h"

Aquarius::Aquarius(const Wt::WEnvironment& env)
    : Wt::WApplication(env)
{

    int ii;

    setTitle("LED Control");
    pwmDriver = new PCA9685(1,0x40);
    powerDriver = new MCP23008(1,0x20);
    powerDriver->setAllOutput();
    root()->addWidget(new Wt::WText("<h2>LED Channels:</h2>"));
    ledTable  = new Wt::WTable(root());
    root()->addWidget(new Wt::WText("<h2>Power Outlets:</h2>"));
    poTable = new Wt::WTable(root());

    for (ii=0; ii<16; ii++){
           LEDChannel *led = new LEDChannel(ii+1);
           leds[ii] = led;
           led->valueChanged().connect(this, &Aquarius::setPWM);
           if (ii < 8)
               ledTable->elementAt(0, ii)->addWidget(led);
           else
               ledTable->elementAt(1,ii-8)->addWidget(led);
        }
    for (ii=0; ii<8; ii++){
           PowerOutlet *po = new PowerOutlet(ii+1);
           pos[ii] = po;
           po->setSelected(powerDriver->get(ii+1));
           po->valueChanged().connect(this, &Aquarius::setOutlet);
           poTable->elementAt(0, ii)->addWidget(po);
        }
}

Aquarius::~Aquarius(){
	delete pwmDriver;
	delete powerDriver;
}

void Aquarius::setOutlet(int pin, int state){
	powerDriver->set(pin, state);
}

void Aquarius::setPWM(int channel, int value)
{
    pwmDriver->setPWM(channel,value);
}

Wt::WApplication *createApplication(const Wt::WEnvironment& env)
{
    return new Aquarius(env);
}

int main(int argc, char **argv)
{
    return Wt::WRun(argc, argv, &createApplication);
}
