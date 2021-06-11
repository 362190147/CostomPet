package top.yumesekai.pet;

class PetC {
    static {
        System.loadLibrary("native-lib");
    }
    native String stringFromJNI();
}
