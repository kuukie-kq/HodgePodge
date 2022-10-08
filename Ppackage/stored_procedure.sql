DROP PROCEDURE IF EXISTS `restore_function_name`;

DELIMITER //
/**
 *  这里将一条语句的结束标志换成//符号，因为存储过程中可能会使用默认结束符;
 *  如果不改变结束符号，则会报SQL语法错
 *  也有特殊情况，好像是存储过程比较简单，SQL解释器能直接分析出来
 */
CREATE PROCEDURE `restore_function_name`(IN _charID BIGINT, OUT _result INT)
BEGIN
    DECLARE EXIT HANDLER FOR SQLEXCEPTION BEGIN ROLLBACK; SELECT _result; END;
    DECLARE EXIT HANDLER FOR SQLSTATE '40001' BEGIN ROLLBACK; SET _result = -98; SELECT _result; END;
    DECLARE EXIT HANDLER FOR SQLSTATE '22003' BEGIN ROLLBACK; SET _result = -97; SELECT _result; END;
    DECLARE CONTINUE HANDLER FOR SQLSTATE '02000' BEGIN END;
    /**
     *  这里是申明变量的部分，也可以申明一些事件的处理
     *  注意，一定要放在存储过程的开头，否则会报语法错误
     *  其中sqlstate为5位16进制的数，表示对应的SQL事件
     */
    SET _result = -100;
    LABEL_RESTORE:BEGIN
        /**
         *  定义一个标签，相当于内部函数
         *  或者是一个语句块，作为标志
         */
        IF EXISTS (SELECT char_id FROM merger_delete_characters WHERE char_id = _charID) THEN
            SET _result = -99;
        ELSE
            SET _result = -95;
            LEAVE LABEL_RESTORE;
        END IF;

        START TRANSACTION;
            /**
             *  开启事务，在碰到commit或rollback之前都是事务内的处理
             *  虽然没有强制要求，不过缩进一下更加直观
             */
            INSERT INTO common_characters SELECT * FROM merger_delete_characters  WHERE char_id = _charID;
            INSERT INTO common_atbs SELECT * FROM merger_delete_atbs  WHERE char_id = _charID;
            INSERT INTO common_quests SELECT * FROM merger_delete_quests  WHERE char_id=_charID;
            INSERT INTO common_quests_done SELECT * FROM merger_delete_quests_done  WHERE char_id=_charID;
            INSERT INTO common_cooldowns SELECT * FROM merger_delete_cooldowns  WHERE char_id=_charID;
            INSERT INTO common_states SELECT * FROM merger_delete_states WHERE char_id=_charID;
            INSERT INTO common_recipes SELECT * FROM merger_delete_recipes WHERE char_id=_charID;
            INSERT INTO common_pets SELECT * FROM merger_delete_pets WHERE char_id=_charID;
            INSERT INTO common_liveness SELECT * FROM merger_delete_liveness WHERE char_id = _charID;
            INSERT INTO common_titles SELECT * FROM merger_delete_titles WHERE char_id=_charID;
            INSERT INTO cdgood SELECT * FROM merger_delete_cdgood WHERE char_id=_charID;
            INSERT INTO common_activity SELECT * FROM merger_delete_activity WHERE char_id=_charID;
            INSERT INTO common_talk_story SELECT * FROM merger_delete_talk_story WHERE char_id=_charID;
            INSERT INTO common_glori_score SELECT * FROM merger_delete_glori_score WHERE char_id=_charID;
            INSERT INTO common_qqfriend SELECT * FROM merger_delete_qqfriend WHERE char_id=_charID;
            INSERT INTO common_avatar SELECT * FROM merger_delete_avatar WHERE char_id=_charID;
            INSERT INTO common_strflag SELECT * FROM merger_delete_strflag WHERE char_id=_charID;
            /**
             *  这种语法为select查找的结果表的数据插入到另一个表
             *  可以结合values语法，处理不同表结构的情况
             *  同表结构，建表可以create table *** like ***;这种形式
             */
            SET _result = -20;
            /**
             *  事务的调试
             *  目前好像是只能通过这种手动插入断点的方式
             */
            INSERT INTO master_archv SELECT * FROM merger_delete_master_archv  WHERE char_id=_charID;
            INSERT INTO pet_col SELECT * FROM merger_delete_pet_col WHERE char_id=_charID;
            INSERT INTO online_items SELECT * FROM merger_delete_items WHERE char_id=_charID;

            SET _result = -23;

            DELETE FROM merger_delete_characters  WHERE char_id = _charID;
            DELETE FROM merger_delete_atbs  WHERE char_id = _charID;
            DELETE FROM merger_delete_quests  WHERE char_id=_charID;
            DELETE FROM merger_delete_quests_done  WHERE char_id=_charID;
            DELETE FROM merger_delete_cooldowns  WHERE char_id=_charID;
            DELETE FROM merger_delete_states WHERE char_id=_charID;
            DELETE FROM merger_delete_recipes WHERE char_id=_charID;
            DELETE FROM merger_delete_pets WHERE char_id=_charID;
            DELETE FROM merger_delete_liveness WHERE char_id = _charID;
            DELETE FROM merger_delete_titles WHERE char_id=_charID;
            DELETE FROM merger_delete_cdgood WHERE char_id=_charID;
            DELETE FROM merger_delete_activity WHERE char_id=_charID;
            DELETE FROM merger_delete_talk_story WHERE char_id=_charID;
            DELETE FROM merger_delete_glori_score WHERE char_id=_charID;
            DELETE FROM merger_delete_qqfriend WHERE char_id=_charID;
            DELETE FROM merger_delete_avatar WHERE char_id=_charID;
            DELETE FROM merger_delete_strflag WHERE char_id=_charID;

            SET _result = -40;

            DELETE FROM merger_delete_master_archv  WHERE char_id=_charID;
            DELETE FROM merger_delete_pet_col WHERE char_id=_charID;
            DELETE FROM merger_delete_items WHERE char_id=_charID;

            SET _result = -46;

            UPDATE common_characters SET delete_time=0,mark_delete=0 WHERE char_id=_charID;
        COMMIT;
        /**
         *  提交事务，这里也就看出开头定义的事件处理的作用了
         *  如果在事务执行过程中出现一些error，则会进行回滚，用来保护数据
         */

        SET _result = 0;
    END LABEL_RESTORE;

    SELECT _result;
END//

DELIMITER ;
/**
 *  同上，最好是再定义一遍
 *  表示以//为结尾不需要了
 *  但是，不声明这个
 *  ;依然可以作为一条语句的结尾，这个可能跟SQL解释器有关
 *  可能只有一行所以即使在声明了//为结尾的情况，;也解释成结尾标志
 */
CALL restore_function_name(1240000000000004076,@result);
/**
 *  注意用户自定义的临时变量必须以@开头
 *  这个变量的作用域为本次连接
 */
DROP PROCEDURE IF EXISTS `restore_function_name`;
