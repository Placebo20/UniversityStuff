clear

X = imread("x3.bmp");
X = double(X);
X = [X; ones(size(X, 2), 1)'];
imshow(uint8(X));

figure
Y = imread("y8.bmp");
Y = double(Y);
imshow(uint8(Y));

PseudoX = Grevil(X);
A = Y * PseudoX + rand(size(Y,1), size(X,1)) * Z(PseudoX, X);
isCorrect = A * X;

figure
imshow(uint8(isCorrect));

PseudoX = MurPenroze(X);
A = Y * PseudoX + rand(size(Y,1), size(X,1)) * Z(PseudoX, X);
isCorrect = A * X;

figure
imshow(uint8(isCorrect));

function valReturn = Z(A, PseudoA)
    valReturn = eye(size(PseudoA, 1)) - PseudoA * A;
end

function valReturn = Grevil(A)
    isSwap = 0;
    if(size(A,1) > size(A,2))
        isSwap = 1;
        A = A';
    end

    currVector = A(1,:)';
    PseudoA = 0;
    currVectorScalar = currVector' * currVector;
    if(currVectorScalar == 0)
        PseudoA = currVector;
    else
        PseudoA = currVector/currVectorScalar;
    end
    iterA = currVector';
    for i = 2: size(A,1)
        currVector = A(i,:)';
        ZA = Z(iterA,PseudoA);
        iterA = [iterA;currVector'];
        denomZ = currVector' * ZA * currVector;
        if(denomZ > 0.000001)
            PseudoA = [(PseudoA-(ZA*currVector*currVector'*PseudoA)/denomZ),(ZA*currVector)/denomZ];
        else
            RA = PseudoA * PseudoA';
            denomR = 1 + currVector' * RA * currVector;
            PseudoA = [(PseudoA - (RA * currVector * currVector' * PseudoA)/denomR),(RA * currVector)/denomR];
        end
    end
    if (isSwap)
        PseudoA = PseudoA';
    end
    valReturn = PseudoA;
end

function valReturn = J(currA, nextA)
    valReturn = max(max((currA-nextA).^2));
end

function valueReturn = MurPenroze(A)
    isSwap = 0;
    if(size(A,1) > size(A,2))
        isSwap = 1;
        A = A';
    end

    epsilon = 1e-8;
    inf = 1e9;
    currPseudoA = inf * ones(size(A))';
    nextPseudoA = -inf * ones(size(A))';
    delta = 10.0;
    counter = 0;
    while(J(currPseudoA, nextPseudoA) > epsilon)
       currPseudoA = nextPseudoA;
       nextPseudoA = A' * inv(A * A' + (delta) * eye(size(A, 1)));
       delta = delta/2.0;
       counter = counter + 1;
       fprintf("%d\n", counter);
    end

    if(isSwap)
        nextPseudoA = nextPseudoA';
    end
    valueReturn = nextPseudoA;
end
