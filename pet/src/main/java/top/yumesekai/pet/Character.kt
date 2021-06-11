package top.yumesekai.pet

import top.yumesekai.pet.Character.Attribution
import java.io.*
import kotlin.Throws

/**
 * 角色类
 * @author wei
 */
class Character {
    inner class Attribution(name: String?, num: Int) {
        var name: String? = null
        var num = 0

        init {
            this.name = name
            this.num = num
        }
    }

    /** 属性 */
    var attri = arrayOfNulls<Attribution>(50)
    fun init() {
        attri[0] = Attribution("life", 100)
        attri[1] = Attribution("lifeMax", 100)
    }

    @Throws(IOException::class)
    fun save(FileName: String?) {
        val file = File(FileName)
        var strAttri = ""
        for (o in attri) {
            if (o!!.name != null) strAttri += o.name + "=" + o.num
        }
        val buffer = strAttri.toByteArray()
        var out: OutputStream? = null
        try {
            out = BufferedOutputStream(FileOutputStream(file))
            out.write(buffer)
        } finally {
            out?.close()
        }
    }

    fun load(FileName: String?) {}

    /**
     * 获得属性
     * @param name 属性名
     * @return 成功返回属性值， 失败返回-1
     */
    fun getAttribution(name: String): Int {
        for (o in attri) {
            if (o!!.name == name) return o.num
        }
        return -1
    }

    /**
     * 设置属性
     * @param name 属性名
     * @param num 属性值
     * @return 成功返回属性值， 失败返回-1
     */
    fun setAttribution(name: String, num: Int): Int {
        for (o in attri) {
            if (o!!.name == name || o.name == null) {
                o.num = num
                return num
            }
        }
        return -1
    }

    init {
        init()
    }
}