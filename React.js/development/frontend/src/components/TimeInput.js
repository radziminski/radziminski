import React, { useState } from 'react';
import { digitToTwoCharString } from '../utils';
import { IoMdArrowDropup, IoMdArrowDropdown } from 'react-icons/io';

const TimeInput = (props) => {
    const [hours, setHours] = useState(props.default.getHours());
    const [minutes, setMinutes] = useState(props.default.getMinutes());

    const addToTimeValue = (time, addValue, limit) => {
        const newTime = time + addValue;
        if (newTime > limit) return newTime - limit - 1;
        if (newTime < 0) return limit + newTime + 1;

        return newTime;
    };

    const onChange = (input, change) => {
        const hoursInDay = 23;
        const minutesInHours = 59;

        let newHours = hours;
        let newMinutes = minutes;

        if (input === 'hours') {
            newHours = addToTimeValue(hours, change, hoursInDay);
            setHours(newHours);
        } else {
            newMinutes = addToTimeValue(minutes, change, minutesInHours);
            setMinutes(newMinutes);
        }

        const retDate = new Date();
        retDate.setHours(newHours, newMinutes, 0, 0);
        props.onChange(retDate);
    };

    return (
        <div className="time-input">
            <h2 className="time-input__label">{props.label}</h2>
            <div className="time-input__time-box">
                <div className="time-input__input">{digitToTwoCharString(hours)}</div>
                <div className="time-input__btns-box">
                    <button
                        type="button"
                        className="time-input__btn"
                        onClick={() => onChange('hours', 1)}
                    >
                        <IoMdArrowDropup className="time-input__icon time-input__icon--up" />
                    </button>
                    <button
                        type="button"
                        className="time-input__btn"
                        onClick={() => onChange('hours', -1)}
                    >
                        <IoMdArrowDropdown className="time-input__icon time-input__icon--down" />
                    </button>
                </div>
                <div className="time-input__input">{digitToTwoCharString(minutes)}</div>
                <div className="time-input__btns-box">
                    <button
                        type="button"
                        className="time-input__btn"
                        onClick={() => onChange('minutes', 1)}
                    >
                        <IoMdArrowDropup className="time-input__icon time-input__icon--up" />
                    </button>
                    <button
                        type="button"
                        className="time-input__btn"
                        onClick={() => onChange('minutes', -1)}
                    >
                        <IoMdArrowDropdown className="time-input__icon time-input__icon--down" />
                    </button>
                </div>
            </div>
        </div>
    );
};

export default TimeInput;
