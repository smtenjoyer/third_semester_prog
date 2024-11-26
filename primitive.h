#pragma once

class Primitive {
public:
    Primitive(const std::string& name) : name_(name) {}
    Primitive() : name_() {}

    void set_name(const std::string& new_name) {
        name_ = new_name;
    }
    std::string get_name() const {
        return name_;
    }
    virtual std::string get_type() const {  // virtual keyword added
        return type_;
    }

private:
    std::string name_ = "none";
    std::string type_ = "some";
};

class Circle : public Primitive {
private:
    double radius_ = 0.0;
public:
    Circle(const std::string& name) : Primitive(name), radius_() {}
    Circle(const std::string& name, double radius) : Primitive(name), radius_(radius) {}
    Circle() : Primitive(), radius_() {}

    void set_radius(double radius) {
        radius_ = radius;
    }
    double get_radius() const {
        return radius_;
    }
    std::string get_type() const override { // override keyword added
        return "circle";
    }
};

class Square : public Primitive {
private:
    double side_ = 0.0;
public:
    Square(const std::string& name, double side) : Primitive(name), side_(side) {}
    Square(const std::string& name) : Primitive(name), side_() {}
    Square() : Primitive(), side_() {}

    void set_side(double side) {
        side_ = side;
    }
    double get_side() const {
        return side_;
    }
    std::string get_type() const override { // override keyword added
        return "square";
    }
};

class Polygon : public Primitive {
private:
    double side_ = 0.0;
    unsigned num_ = 0;
public:
    Polygon(const std::string& name, double side, unsigned num) : Primitive(name), side_(side), num_(num) {}
    Polygon(const std::string& name) : Primitive(name), side_(), num_() {}
    Polygon() : Primitive(), side_(), num_() {}

    void set_num(unsigned num) {
        num_ = num;
    }
    unsigned get_num() const {
        return num_;
    }
    std::string get_type() const override { // override keyword added
        return "polygon";
    }
};
