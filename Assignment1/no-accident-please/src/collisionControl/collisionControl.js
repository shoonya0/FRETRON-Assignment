// Function to calculate the intersection point of two line segments
function lineIntersection(A, B, C, D) {
  const [x1, y1] = A;
  const [x2, y2] = B;
  const [x3, y3] = C;
  const [x4, y4] = D;

  const denom = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);
  if (denom === 0) {
    return null; // Lines are parallel or coincident
  }

  const t = ((x1 - x3) * (y3 - y4) - (y1 - y3) * (x3 - x4)) / denom;
  const u = -((x1 - x2) * (y1 - y3) - (y1 - y2) * (x1 - x3)) / denom;

  if (0 <= t && t <= 1 && 0 <= u && u <= 1) {
    const intersectionX = x1 + t * (x2 - x1);
    const intersectionY = y1 + t * (y2 - y1);
    return [intersectionX, intersectionY];
  }

  return null; // No intersection within the segments
}

// Function to check for intersections between two flights and add a point if necessary
function checkOnTwoFlight(flight1, flight2) {
  let intersectionDetected = true;

  while (intersectionDetected) {
    intersectionDetected = false;

    for (let i = 1; i < flight1.length && i < flight2.length; i++) {
      const A = flight1[i - 1];
      const B = flight1[i];
      const C = flight2[i - 1];
      const D = flight2[i];

      const intersection = lineIntersection(A, B, C, D);
      if (intersection) {



        console.log(`Intersection detected at: (${intersection[0]}, ${intersection[1]})`);
        intersectionDetected = true;

        // Calculate midpoints to add around the intersection
        const midPoint1 = [(A[0] + intersection[0]) / 2, (A[1] + intersection[1]) / 2];
        const midPoint2 = [(D[0] + intersection[0]) / 2, (D[1] + intersection[1]) / 2];

        // Add new points to both flight paths
        flight1.splice(i, 0, midPoint1);
        flight2.splice(i, 0, midPoint2);

        // Exit the loops to restart checking from the beginning
        break;
      }
      if (intersectionDetected) break;
    }
  }
}


// const flight1 = [
//   [0, 0],
//   [1, 1],
//   [2, 2],
//   [3, 3]
// ];

// const flight2 = [
//   [0, 3],
//   [1, 2],
//   [2, 1],
//   [3, 0]
// ];
function collisionControl(data) {
  const flight1 = data.flight1;
  const flight2 = data.flight2;
  const flight3 = data.flight3;

  // Check for intersections between flight1 and flight2
  checkOnTwoFlight(flight1, flight2);
  checkOnTwoFlight(flight1, flight3);
  checkOnTwoFlight(flight2, flight3);

  return { flight1, flight2 };
}

// collisionControl(flight1, flight2);

export default collisionControl;