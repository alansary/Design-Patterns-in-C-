#include <iostream>
#include <list>
using namespace std;

class IObserver {
public:
	virtual ~IObserver() {}
	virtual void Update() = 0;
};

class IObservable {
public:
	virtual ~IObservable() {}
	virtual void Attach(IObserver *observer) = 0;
	virtual void Detach(IObserver *observer) = 0;
	virtual void Notify() = 0;
};

class WeatherStation : public IObservable {
private:
	list<IObserver *> observers_;
	double temperature;

public:
	WeatherStation() {
		temperature = 0.0;
	}

	void Attach(IObserver *observer) override {
		this->observers_.push_back(observer);
	}

	void Detach(IObserver *observer) override {
		this->observers_.remove(observer);
	}

	void Notify() override {
//	    list<IObserver *>::iterator iterator = observers_.begin();
//	    while (iterator != observers_.end()) {
//	    	(*iterator)->Update();
//	    	++iterator;
//	    }
	    for (IObserver * observer : observers_) {
	    	observer->Update();
	    }
	}

	void SetState(double temp) {
		this->temperature = temp;
		this->Notify();
	}

	double GetState() {
		return this->temperature;
	}
};

class PhoneDisplay : public IObserver {
private:
	WeatherStation *weather_station_;
public:
	PhoneDisplay(WeatherStation *weather_station) {
		this->weather_station_ = weather_station;
		this->weather_station_->Attach(this);
	}

	void Update() override {
		cout << "Observer: " << this << ", State: " << this->weather_station_->GetState() << endl;
	}
};

class WindowDisplay : public IObserver {
private:
	WeatherStation *weather_station_;
public:
	WindowDisplay(WeatherStation *weather_station) {
		this->weather_station_ = weather_station;
		this->weather_station_->Attach(this);
	}

	void Update() override {
		cout << "Observer: " << this << ", State: " << this->weather_station_->GetState() << endl;
	}
};

int main() {
	WeatherStation *weather_station = new WeatherStation();
	PhoneDisplay *phone_display = new PhoneDisplay(weather_station);
	WindowDisplay *window_display = new WindowDisplay(weather_station);
	weather_station->SetState(1.0);
	weather_station->SetState(2.0);
	weather_station->SetState(3.0);

	return 0;
}
