import React from 'react';

const Day = (props) => {
    return (
        <div className={props.className} onClick={props.onClick} data-isactive={props.active}>
            {props.children}
        </div>
    );
};

export default Day;
