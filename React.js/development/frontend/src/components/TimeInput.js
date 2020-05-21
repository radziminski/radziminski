import React, { useState } from 'react';
import { timeToString } from '../utils';
import { IoMdArrowDropup, IoMdArrowDropdown } from 'react-icons/io';

const TimeInput = (props) => {
    const [hours, setHours] = useState(0);
    const [minutes, setMinutes] = useState(0);

    const addToTimeValue = (time, addValue, limit) => {
        const newTime = time + addValue;
        if (newTime > limit) return newTime - limit - 1;
        if (newTime < 0) return limit + newTime + 1;

        return newTime;
    };

    const hoursInDay = 23;
    const minutesInHours = 59;

    return (
        <div className="time-input">
            <h2 className="time-input__label">{props.label}</h2>
            <div className="time-input__time-box">
                <div className="time-input__input">{timeToString(hours)}</div>
                <div className="time-input__btns-box">
                    <button
                        type="button"
                        className="time-input__btn"
                        onClick={() => setHours(addToTimeValue(hours, 1, hoursInDay))}
                    >
                        <IoMdArrowDropup className="time-input__icon time-input__icon--up" />
                    </button>
                    <button
                        type="button"
                        className="time-input__btn"
                        onClick={() => setHours(addToTimeValue(hours, -1, hoursInDay))}
                    >
                        <IoMdArrowDropdown className="time-input__icon time-input__icon--down" />
                    </button>
                </div>
                <div className="time-input__input">{timeToString(minutes)}</div>
                <div className="time-input__btns-box">
                    <button
                        type="button"
                        className="time-input__btn"
                        onClick={() => setMinutes(addToTimeValue(minutes, 1, minutesInHours))}
                    >
                        <IoMdArrowDropup className="time-input__icon time-input__icon--up" />
                    </button>
                    <button
                        type="button"
                        className="time-input__btn"
                        onClick={() => setMinutes(addToTimeValue(minutes, -1, minutesInHours))}
                    >
                        <IoMdArrowDropdown className="time-input__icon time-input__icon--down" />
                    </button>
                </div>
            </div>
        </div>
    );
};

export default TimeInput;
