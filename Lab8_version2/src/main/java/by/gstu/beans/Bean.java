package by.gstu.beans;

import java.util.Objects;

public abstract class Bean {
    private int id;

    public Bean(){}
    public Bean(int id){
        this.id = id;
    }

    public int getId(){return id;}
    public void setId(int id){
        this.id = id;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (!(o instanceof Bean)) return false;
        Bean bean = (Bean) o;
        return getId() == bean.getId();
    }

    @Override
    public int hashCode() {
        return Objects.hash(getId());
    }

    @Override
    public String toString() {
        return "{id:" + id + ",";
    }
}
