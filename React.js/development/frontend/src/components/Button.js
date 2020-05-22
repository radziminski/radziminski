import React from 'react';

const Button = (props) => {
    let className = 'btn';
    // Handling style types
    if (props.classTypes) className += ' btn--' + props.classTypes.join(' btn--');

    // Handling form types
    if (props.type)
        return (
            <button type={props.type} className={className} onClick={props.onClick}>
                {props.children}
            </button>
        );

    return (
        <button className={className} onClick={props.onClick}>
            {props.children}
        </button>
    );
};

export default Button;
