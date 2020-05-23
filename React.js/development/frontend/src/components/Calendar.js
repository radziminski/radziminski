import React, { useState, useEffect } from 'react';
import { getMonthStringFromDate, addDaysToDate, compareDates } from '../utils';
import axios from 'axios';
import { withRouter } from 'react-router-dom';
import Day from './DayCell';
import Navbar from './Navbar';

const weekDays = ['Mon', 'Tue', 'Wen', 'Thu', 'Fri', 'Sat', 'Sun'];

export const Calendar = (props) => {
    // If user goes back from not current month
    const defaultDate = props.match.params.date
        ? new Date(props.match.params.date * 1) // * 1 used to convert to int
        : new Date();

    // State
    const [currDate, setCurrDate] = useState(defaultDate);
    const [daysWithEvents, setDaysWithEvents] = useState([]);

    // Getting all events once after component mounts
    useEffect(() => {
        axios
            .get('/api/events')
            .then((data) => data.data.data)
            .then((data) => JSON.parse(data)) // data comes in serialized json
            .then((data) => {
                const events = data.map((el) => {
                    return {
                        id: el.Id,
                        description: el.Description,
                        date: new Date(el.Date),
                    };
                });
                setDaysWithEvents(events);
            })
            .catch((err) => {
                if (props.match.params.date)
                    console.error('Could not connect to the server.\n', err);
                else
                    alert(
                        'Sorry, something went wrong while connecting to server. Please make sure that the server is properly running.\n' +
                            err
                    );
            });
        // disablaing message since its a method used in other places too
        // eslint-disable-next-line react-hooks/exhaustive-deps
    }, []);

    // Function creating days visible in given month
    const generateDays = (events = []) => {
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
            // Adding hasEvent flag to know if daay needs to be blue
            let hasEvent = false;
            if (events.find((el) => compareDates(el.date, date))) hasEvent = true;

            days.push({
                date: date.getDate(),
                active: date.getMonth() === currDate.getMonth(),
                event: hasEvent,
                today: compareDates(date, new Date()),
                sunday: date.getDay() === 0,
            });

            // Moving to next day
            addDaysToDate(date, 1);
            dayCounter++;
        }
        return days;
    };

    // If days is clicked going to day view
    const onDayClicked = (e) => {
        // Defining date
        const day = e.target.innerText;
        let month = currDate.getMonth();
        let year = currDate.getFullYear();

        // Cases where date from other month was clicked
        if (e.target.getAttribute('data-isactive') === 'false') {
            if (day > 20) month--;
            else month++;
        }

        // Cases where date from other year was clicked
        if (month > 11) {
            month = 0;
            year++;
        }
        if (month < 0) {
            month = 11;
            year--;
        }

        // Switching view with React Router
        props.history.push(`/day/${new Date(year, month, day).getTime()}`);
    };

    // Handling if month has been changed by arrow on navbar
    const onMonthChanged = (offset) => {
        const date = new Date(currDate);
        let newMonth = date.getMonth() + offset;

        // Handling if year was changed
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

    // Creating days DOM elements
    const days = generateDays(daysWithEvents).map(({ date, active, event, today, sunday }, i) => (
        <Day
            key={i}
            className={`calendar__day ${!active ? 'calendar__day--ghost' : ''} ${
                event ? 'calendar__day--event' : ''
            } ${today ? 'calendar__day--today' : ''} ${sunday ? 'calendar__day--red' : ''}`}
            onClick={onDayClicked}
            active={active}
        >
            {date}
        </Day>
    ));

    return (
        <div className="calendar">
            <Navbar
                onLeftClick={() => onMonthChanged(-1)}
                onRightClick={() => onMonthChanged(1)}
                title={`${getMonthStringFromDate(currDate)} ${currDate.getFullYear()}`}
            />
            <ul className="calendar__week-days">
                {weekDays.map((el, id) => (
                    <li key={id} className="calendar__week-day">
                        {el}
                    </li>
                ))}
            </ul>
            <div className="calendar__days-box">{days}</div>
        </div>
    );
};

export default withRouter(Calendar);
