import React from 'react';
import { IoIosArrowDropleft, IoIosArrowDropright } from 'react-icons/io';

const Navbar = (props) => {
    return (
        <div className="calendar__navbar">
            <div className="calendar__arrow" onClick={props.onLeftClick}>
                <IoIosArrowDropleft className="calendar__icon" />
            </div>
            <h1 className="calendar__title">{props.title}</h1>
            <div className="calendar__arrow" onClick={props.onRightClick}>
                <IoIosArrowDropright className="calendar__icon" />
            </div>
        </div>
    );
};

export default Navbar;
