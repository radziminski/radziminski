import React, { useState } from 'react';
import { getMonthStringFromDate, addDaysToDate } from '../utils';
import { IoIosArrowDropleft, IoIosArrowDropright } from 'react-icons/io';

export const Calendar = (props) => {
    const [currDate, setCurrDate] = useState(props.currDate);
    const [daysWithEvents, setDaysWithEvents] = useState([]);

    const generateDays = () => {
        const days = [];
        const date = new Date(currDate);
        date.setDate(1);
        // Starting from some days from previous month:
        while (date.getDay() !== 1) date.setDate(date.getDate() - 1);

        // Generating the days:
        const daysRows = 6;
        const daysInWeek = 7;

        let dayCounter = 0;
        while (dayCounter < daysRows * daysInWeek) {
            days.push({
                date: date.getDate(),
                active: date.getMonth() === currDate.getMonth(),
            });
            addDaysToDate(date, 1);
            dayCounter++;
        }
        return days;
    };

    const onDayClicked = (e) => {
        const day = e.target.innerText;
        const date = currDate;
        date.setDate(day);
        if (e.target.classList.length > 1) {
            if (day > 20) date.setMonth(date.getMonth() - 1);
            else date.setMonth(date.getMonth() + 1);
        }
        props.switchView('day', date);
    };

    const onMonthChanged = (offset) => {
        const date = new Date(currDate);
        let newMonth = date.getMonth() + offset;
        if (newMonth > 11) {
            newMonth = 0;
            date.setFullYear(date.getFullYear() + 1);
        }
        if (newMonth < 0) {
            newMonth = 11;
            date.setFullYear(date.getFullYear() - 1);
        }
        date.setMonth(newMonth);

        setCurrDate(date);
    };

    const days = generateDays(currDate).map(({ date, active }, i) => (
        <div
            key={i}
            className={`calendar__day ${!active ? 'calendar__day--ghost' : ''}`}
            onClick={onDayClicked}
        >
            {date}
        </div>
    ));

    return (
        <div className="calendar">
            <div className="calendar__navbar">
                <div className="calendar__arrow" onClick={() => onMonthChanged(-1)}>
                    <IoIosArrowDropleft className="calendar__icon" />
                </div>
                <h1 className="calendar__title">{getMonthStringFromDate(currDate)}</h1>
                <div className="calendar__arrow" onClick={() => onMonthChanged(1)}>
                    <IoIosArrowDropright className="calendar__icon" />
                </div>
            </div>
            <div className="calendar__days-box">{days}</div>
        </div>
    );
};

export default Calendar;
