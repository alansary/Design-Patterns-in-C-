#include <iostream>
using namespace std;

class IQuackBehavior {
public:
	virtual ~IQuackBehavior() {} // Prevent memory leaks
	virtual void Quack() const = 0;
};

class SimpleQuack : public IQuackBehavior {
public:
	void Quack() const override {
		cout << "Simple Quack" << endl;
	}
};

class NoQuack : public IQuackBehavior {
public:
	void Quack() const override {
		cout << "No Quack" << endl;
	}
};

class IDisplayBehavior {
public:
	virtual ~IDisplayBehavior() {}
	virtual void Display() const = 0;
};

class GraphicsDisplay : public IDisplayBehavior {
public:
	void Display() const override {
		cout << "Graphics Display" << endl;
	}
};

class TextDisplay : public IDisplayBehavior {
public:
	void Display() const override {
		cout << "Text Display" << endl;
	}
};

class IFlyBehavior {
public:
	virtual ~IFlyBehavior() {}
	virtual void Fly() const = 0;
};

class JetFly : public IFlyBehavior {
public:
	void Fly() const override {
		cout << "Jet Fly" << endl;
	}
};

class NoFly : public IFlyBehavior {
public:
	void Fly() const override {
		cout << "No Fly" << endl;
	}
};

class Duck {
private:
	IQuackBehavior* qb_;
	IDisplayBehavior* db_;
	IFlyBehavior* fb_;
public:
	Duck(IQuackBehavior* qb, IDisplayBehavior* db, IFlyBehavior* fb) {
		qb_ = qb;
		db_ = db;
		fb_ = fb;
	}

	~Duck() {
		delete this->qb_;
		delete this->db_;
		delete this->fb_;
	}

	void Quack() {
		this->qb_->Quack();
	}

	void Display() {
		this->db_->Display();
	}

	void Fly() {
		this->fb_->Fly();
	}
};

void ClientCode()
{
    Duck *duck = new Duck(new SimpleQuack, new TextDisplay, new NoFly);
    duck->Quack();
    duck->Display();
    duck->Fly();
    delete duck;
}

int main() {
	ClientCode();

	return 0;
}
