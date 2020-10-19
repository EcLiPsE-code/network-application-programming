package beans;

import beans.enums.TypeShip;

import java.io.Serializable;
import java.util.Objects;

public class Ship extends Bean implements Cloneable, Serializable {

    private String shipName;
    private TypeShip typeShip;
    private double displacement;  //водоизмещение
    private String country;  //страна-производитель

    public Ship(){}
    public Ship(int id, String shipName, TypeShip typeShip, double displacement, String country){
        super.setId(id);
        this.shipName = Objects.requireNonNull(shipName);
        this.typeShip = Objects.requireNonNull(typeShip);
        this.displacement = displacement;
        this.country = Objects.requireNonNull(country);
    }
    public Ship(String shipName, TypeShip typeShip, double displacement, String country){
        this.shipName = Objects.requireNonNull(shipName);
        this.typeShip = Objects.requireNonNull(typeShip);
        this.displacement = displacement;
        this.country = Objects.requireNonNull(country);
    }

    @Override
    public boolean equals(Object o) {
       if (Objects.equals(o, null)) return false;
       if (getClass() != o.getClass()) return false;
       if (!super.equals(o)) return false;
       Ship ship = (Ship)o;
       return Objects.equals(shipName, ship.shipName) &&
               Objects.equals(typeShip, ship.typeShip) &&
               displacement == ship.displacement &&
               Objects.equals(country, ship.country);
    }

    @Override
    public int hashCode() {
        return super.hashCode() + Objects.hash(shipName, typeShip, displacement, country);
    }

    @Override
    public String toString() {
        return getClass().getName() + "[" +
                "id: " + super.toString() +
                "shipName: " + shipName +
                ",typeShip: " + typeShip +
                ",displacment: " + displacement +
                ",country: " + country + "]";
    }
}
