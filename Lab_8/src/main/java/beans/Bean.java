package beans;

import java.util.Objects;

public class Bean {
    static {
        beanId = 0;
    }
    private static int beanId;
    private int id;

    public Bean(){
        beanId = getBeanId() + 1;
    }

    public int getBeanId(){
        return beanId;
    }

    public int getId(){ return this.id; }
    public void setId(int id){
        this.id = id;
    }

    @Override
    public boolean equals(Object o) {
        if (Objects.equals(o, null)) return false;
        if (getClass() != o.getClass()) return false;
        if (Objects.equals(this, o)) return true;
        Bean bean = (Bean) o;
        return Objects.equals(this.id, bean.id);
    }

    @Override
    public int hashCode() {
        return Objects.hash(id);
    }

    @Override
    public String toString() {
        return "id: " + id;
    }
}
